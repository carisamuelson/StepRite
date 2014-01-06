<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| User Management Model
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/

class User_model extends StepRite_Model {
	
	public function __construct() {
		parent::__construct();
		
		$this->load->library('encrypt');
	}
		
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Get_User_Id
	|--------------------------------------------------------------------------
	|
	| Returns the user_id associated to an email address. Must pass email
	| address to the function
	|
	***************************************************************************/
	public function get_user_id($email) {
		$query = $this->db->get_where('users', array('email' => $email));
		$row = $query->row();
		return $row->id;
	}

	/***************************************************************************
	|--------------------------------------------------------------------------
	| Get_User
	|--------------------------------------------------------------------------
	|
	| Returns all row data associated to a user's email address, or will return
	| a false if row is empty. Must pass email address to the function
	|
	***************************************************************************/
	public function get_user($email) {
		
		$this->db->where('email', $email);
		$query = $this->db->get('users');
		
		if($query->num_rows() > 0) {
			return $query->row_array();
		}
		return false;
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Get_Patient_By_Id
	|--------------------------------------------------------------------------
	|
	| Returns all row data associated to a user's id, or will return
	| a false if row is empty. Must pass id to the function
	|
	***************************************************************************/
	public function get_patient_by_id($id) {
		$query = $this->db->select('*')->from('users')->join('patients', 'users.id = patients.user_id', 'left')->where('users.id', $id)->get();
		
		if($query->num_rows() > 0) {
			return $query->row_array();
		}
		
		return false;
		
	}		

	/***************************************************************************
	|--------------------------------------------------------------------------
	| Get_Patients
	|--------------------------------------------------------------------------
	|
	| Returns all patients associated to a provider's id
	|
	***************************************************************************/
	public function get_patients($id) {
		$query = $this->db->select('*')->from('users')->join('patients', 'users.id = patients.user_id', 'left')->where('patients.provider_id', $id)->where('active',1)->get();
		
		if($query->num_rows() > 0) {
			return $query;
		}
		
		return false;
		
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Get_Provider_By_Id
	|--------------------------------------------------------------------------
	|
	| Returns all row data associated to a user's id, or will return
	| a false if row is empty. Must pass id to the function
	|
	***************************************************************************/
	public function get_provider_by_id($id) {
		$query = $this->db->select('*')->from('users')->join('providers', 'users.id = providers.user_id', 'left')->where('users.id', $id)->get();
		
		if($query->num_rows() > 0) {
			return $query->row_array();
		}
		
		return false;
		
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Insert_Provider
	|--------------------------------------------------------------------------
	|
	| Uses the post data to insert a new provider into the system.
	|
	***************************************************************************/
	public function insert_provider($user_data, $provider_data) {
		
		if($this->db->insert('users', $user_data)) {
			/* get user id to insert provider specific information */
			$id = $this->get_user_id($this->input->post('email'));
			$provider_data['user_id'] = $id;
			$this->db->insert('providers', $provider_data);		
		}
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| insert_Patient
	|--------------------------------------------------------------------------
	|
	| Creates a new patient from the post data
	|
	***************************************************************************/
	public function insert_patient($user_data, $patient_data) {
		
		$password = "password"; // need to change to generate a random password
		$user_data['password'] = $this->encrypt->encode($password);
		
		if($this->db->insert('users', $user_data)) {
			/* get user id to insert patient specific information */
			$id = $this->user_model->get_user_id($this->input->post('email'));
			$patient_data['user_id'] = $id;
			$this->db->insert('patients', $patient_data);
		}
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Change_Password
	|--------------------------------------------------------------------------
	|
	| Compares the current password with the given password. If the two are
	| the same, encrypts the new password and stores it in the database.
	|
	***************************************************************************/	
	public function change_password($password) {
		$data = array(
		   'password' => $this->encrypt->encode($password)
		);

		$this->db->where('id', $this->session->userdata('user_id'));
		$this->db->update('users', $data);
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Check_Password
	|--------------------------------------------------------------------------
	|
	| Compares the current password with the given password. If the two are
	| the same, returns a true. Otherwise, returns false.
	|
	***************************************************************************/	
	public function check_password($password) {
		$this->db->where('id', $this->session->userdata('user_id'));
		$query = $this->db->get('users');
		$row = $query->row();
		
		if($query->num_rows() > 0 && $this->encrypt->decode($row->password) == $password) {
			return true;
		}
		return false;
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Reset_Password
	|--------------------------------------------------------------------------
	|
	| Resets a password associated to an email and sends an email to the user
	| to log in with the temporary password created here.
	|
	***************************************************************************/		
	public function reset_password($email) {
		date_default_timezone_set('GMT');
		$this->load->helper('string');
		$password = random_string('alnum', 12);
		
		echo $password;
		
		$this->db->where('email', $email);
		$query = $this->db->get('users');
		
		if($query->num_rows() > 0) {
			if($this->db->update('users',array('password'=> $this->encrypt->encode($password)))) {
				echo "TRUE";
				return true;
			}
		}
		return false;
		
	}
}
/**** END OF FILE ****/