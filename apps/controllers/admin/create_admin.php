<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Create_admin 
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Create_admin extends StepRite_Controller {
	
	function __construct() {
		parent::__construct();
		if(!$this->session->userdata('admin_logged_in') || $this->session->userdata('admin_type') != 1) {
			redirect('admin/login');
		}
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
		/* Validate the form */
		$this->form_validation->set_rules('first_name', 'Email', 'required');
		$this->form_validation->set_rules('last_name', 'Last Name', 'required');
		$this->form_validation->set_rules('email', 'Email', 'required|valid_email|is_unique[admin.email]');
		$this->form_validation->set_rules('password', 'Password', 'required|min_length[6]|max_length[14]|matches[confirm_password]');
		$this->form_validation->set_rules('confirm_password', 'Password Confirmation', 'required|min_length[6]|max_length[14]');

		if(!$this->form_validation->run()) {
			/************************/
			/*    Load File View    */
			/************************/			
			$data['header_info'] = "Please complete all fields:";
			$data['view'] = 'admin/create_admin';
			$this->load->view('admin/init', $data);
		}
		else {
			// /* insert data into the database */
			$this->load->model('admin/admin_model');
			if($this->admin_model->insert_admin()) {
				$this->session->set_userdata('notice', 'You have successfully created a new employee account');
			}
			else {
				$this->session->set_userdata('notice', 'Unable to communicate with the database');
			}

			/************************/
			/*    Load File View    */
			/************************/
			redirect('admin/admin');
		}
	}
}
/**** END OF FILE ****/