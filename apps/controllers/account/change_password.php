<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Change_password
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Change_password extends StepRite_Controller {
	
	function __construct() {
		parent::__construct();

		$this->load->model('user_model');
	}
	
	public function index() {
		$this->form_validation->set_rules('current_password', 'Current Password', 'required|min_length[6]|max_length[14]|callback__current_password_check');	
		$this->form_validation->set_rules('password', 'Password', 'required|min_length[6]|max_length[14]|matches[confirm_password]');
		$this->form_validation->set_rules('confirm_password', 'Password Confirmation', 'required|min_length[6]|max_length[14]');

		if(!$this->form_validation->run()) {
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = "Please complete all fields";
			$data['view'] = 'account/change_password_form';
			$this->load->view('init', $data);
		}
		else {
			$this->user_model->change_password($this->input->post('password'));
			/************************/
			/*    Load File View    */
			/************************/
			$this->session->set_userdata('notice', 'Your password has been updated');
			redirect('account/account', 'refresh');
		}
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Private Function
	| current_password_check
	|--------------------------------------------------------------------------
	|
	| Calls the model function that compares submitted password to current
	| password to make sure that it is the same
	|
	***************************************************************************/		
	public function _current_password_check($password) {
		if($this->user_model->check_password($password)) {
			return true;
		}
		
		$this->form_validation->set_message('current_password_check', 'The %s field is incorrect.');
		return FALSE;
	}
}
/**** END OF FILE ****/