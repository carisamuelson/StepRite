<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Admin Management Model
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/

class Admin_model extends StepRite_Model {
	
	public function __construct() {
		parent::__construct();
		
		$this->load->library('encrypt');
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Get_admin
	|--------------------------------------------------------------------------
	|
	| Retrieves all info related to an administration's username. If username
	| does not exist, returns a false. Must pass the username with function call
	|
	***************************************************************************/
	public function get_admin($username) {
		$this->db->where('username', $username);
		$query = $this->db->get('admin');
		
		if($query->num_rows() > 0) {
			return $query->row_array();
		}
		return false;
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Insert_Admin
	|--------------------------------------------------------------------------
	|
	| Uses the post data to insert a new provider into the system.
	|
	***************************************************************************/
	public function insert_admin() {
		// create user array
		$data = array(
			'username'		=> $this->input->post('username'),
			'first_name' 	=> $this->input->post('first_name'),
			'last_name' 	=> $this->input->post('last_name'),
			'password'	 	=> $this->encrypt->encode($this->input->post('password')),
			'email '		=> $this->input->post('email'),
			'type'			=> $this->input->post('type')
		);
		// insert new user
		$this->db->insert('admin', $data);
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
	public function change_password($original_password, $password) {
		$this->db->where('id', $this->session->userdata('id'));
		$query = $this->db->get('admin');
		$row = $query->row();
		
		if($this->encrypt->decode($row->password) == $original_password) {
			$data = array(
			   'password' => $this->encrypt->encode($password)
			);

			$this->db->where('id', $this->session->userdata('id'));
			$this->db->update('admin', $data);
			return true;
		}
		return false;
	}

	/***************************************************************************
	|--------------------------------------------------------------------------
	| Insert_Article
	|--------------------------------------------------------------------------
	|
	| Inserts a new article in the database
	|
	***************************************************************************/		
	public function insert_article($name, $article) {
		// create data array
		$data = array(
			'name'			=> $name,
			'article'		=> $article,
			'entry_date'	=> date("Y-m-d")
		);
		// insert article
		$this->db->insert('articles', $data);		
	}
}
/**** END OF FILE ****/