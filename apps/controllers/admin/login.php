<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Login (admin)
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Login extends StepRite_Controller {

	public function __construct() {
		parent::__construct();
		if($this->session->userdata('admin_logged_in')) {
			redirect('admin/admin', 'refresh');
		}
		$this->load->model('admin/admin_model');
		$this->load->library('encrypt');
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Index
	|--------------------------------------------------------------------------
	|
	| Displays the start information related to this class
	|
	***************************************************************************/	
	public function index() {
		$this->form_validation->set_rules('username', 'Username', 'required');
		$this->form_validation->set_rules('password', 'Password', 'required|callback__verify_login');
		
		if(!$this->form_validation->run()) {
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = "Please login to continue:";
			$data['view'] = 'admin/login';
			$this->load->view('admin/init', $data);
		}
		else {
			$this->session->set_userdata('success', 'Thank you for logging in ' . $this->session->userdata('admin_first_name') . " " . $this->session->userdata('admin_last_name'));
			redirect('admin/admin', 'refresh');
		}
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Private Function
	| _verify_Login
	|--------------------------------------------------------------------------
	|
	| Checks to make sure admin account exists, and password entered matches
	| the encrypted password stored in the database related to the username
	| entered.
	|
	***************************************************************************/	
	function _verify_login($password) {
		$q = $this->admin_model->get_admin($this->input->post('username'));
		
		if($q && $password == $this->encrypt->decode($q['password'])) {
			$this->session->set_userdata('admin_logged_in' ,TRUE);
			$this->session->set_userdata('admin_first_name', $q['first_name']);
			$this->session->set_userdata('admin_last_name', $q['last_name']);
			$this->session->set_userdata('admin_id', $q['id']);
			$this->session->set_userdata('admin_type', $q['type']);
			return TRUE;
		}
		
		$this->form_validation->set_message('_verify_password', 'The username or password is invalid');
		return FALSE;	
	}
}
/**** END OF FILE ****/