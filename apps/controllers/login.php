<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Login (Users)
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Login extends StepRite_Controller {
	
	function __construct() {
		parent::__construct();
		if($this->session->userdata('logged_in')) {
			redirect('account/account', 'refresh');
		}
		$this->load->model('user_model');
		$this->load->model('articles_model');
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
	function index() {
		$this->form_validation->set_rules('email', 'Email', 'required');
		$this->form_validation->set_rules('password', 'Password', 'required|callback__verify_login');
		
		if(!$this->form_validation->run()) {
		
			
			$query = $this->articles_model->get_articles();
			
			if ($query->num_rows() > 0) {
				foreach ($query->result() as $row) {
					$data['articles'][] = array(
						'name'		=> $row->name,
						'article'	=> $row->article,
						'date'		=> $row->entry_date
					);
				}
			}
		
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = "Please login to access the dashboards:";
			$data['view'] = 'login';
			$this->load->view('init', $data);
		}
		else {
			if($this->session->userdata('user_type') == 1) {
				redirect('account/account', 'refresh');
			}
			else {
				redirect('patient/account', 'refresh');
			}
		}
	}

	/***************************************************************************
	|--------------------------------------------------------------------------
	| Private Function
	| _verify_Login
	|--------------------------------------------------------------------------
	|
	| Checks for the existence of an email address, a matching password, and 
	| an active account. If all cases succeed, sets the session data
	|
	***************************************************************************/		
	function _verify_login($password) {
		$q = $this->user_model->get_user($this->input->post('email'));
		
		if(!$q) {
			$this->form_validation->set_message('_verify_login', 'The email entered is invalid');
			return FALSE;
		}
		else {
			if($password != $this->encrypt->decode($q['password'])) {
				$this->form_validation->set_message('_verify_login', 'The password entered is invalid');
				return FALSE;
			}
			if(!$q['active']) {
				$this->form_validation->set_message('_verify_login', 'The account is not active. Please wait for customer service to contact you to active your account. Thank you');
				return FALSE;
			}
		}
		
		$this->session->set_userdata('logged_in' ,TRUE);
		$this->session->set_userdata('user_id', $q['id']);
		$this->session->set_userdata('user_type' ,$q['type']);
		$this->session->set_userdata('first_name', $q['first_name']);
		$this->session->set_userdata('last_name', $q['last_name']);
		
		return TRUE;
	}
}
/**** END OF FILE ****/