<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Forgot
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Forgot extends StepRite_Controller {
	function __construct() {
		parent::__construct();
		$this->load->helper('captcha');
		$this->load->model('user_model');
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
		$this->form_validation->set_rules('email', 'Email', 'required|valid_email|callback__email_exists');
		$this->form_validation->set_rules('captcha', "Captcha", 'required|callback__captcha_validation');
		
		if(!$this->form_validation->run()) {
			/* Setup values to pass into the create_captcha function */
			$vals = array(
				'img_path'	 => './captcha/',
				'img_url'	 => base_url() . 'captcha/',
				'font_path'	 => './system/fonts/texb.ttf',
				'img_width'	 => 200,
				'img_height' => 45,
				'expiration' => 600
			);

			/* Generate the captcha */
			$data['captcha'] = create_captcha($vals);

			/* Store the captcha value (or 'word') in a session to retrieve later */
			$this->session->set_flashdata('captcha_word', $data['captcha']['word']);
			
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = 'Please enter your email address below and we\'ll email you a link to reset your password:';
			$data['view'] = 'forgot';
			$this->load->view('init', $data);
		}
		else {
			/************************/
			/*    Load File View    */
			/************************/
			$this->session->set_userdata('notice', 'Your password has been reset. Please follow the directions in your email to complete the password reset process.');
			redirect('login', 'refresh');
		}
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Private Function
	| email_exists
	|--------------------------------------------------------------------------
	|
	| Checks that password entered exists in the database
	|
	***************************************************************************/	
	function _email_exists($email) {
		if($this->user_model->get_user($email)) {
			return TRUE;
		}
		
		$this->form_validation->set_message('_verify_login', 'The email entered is invalid');
		return FALSE;
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Private Function
	| captcha_validation
	|--------------------------------------------------------------------------
	|
	| Compares the captcha word generated to the captcha word submitted by the
	| user.
	|
	***************************************************************************/		
	function _captcha_validation($captcha) {
		if(strtoupper($this->session->flashdata('captcha_word')) == strtoupper($captcha)) {	
			return TRUE;
		}
		
		$this->form_validation->set_message('_captcha_validation', 'The %s field must match the captcha image');
		return FALSE;
	}	
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| send_mail
	|--------------------------------------------------------------------------
	|
	| Sends an email to the user with a link to reset their password
	|
	***************************************************************************/		
	function send_mail($subject, $message, $email) {
		return true;
	}
}
/**** END OF FILE ****/