<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Register_provider
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Register_provider extends StepRite_Controller {
	
	public function __construct() {
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
	function index() {
		/* Validate the form */
		$this->form_validation->set_rules('first_name', 'First Name', 'required');
		$this->form_validation->set_rules('last_name', 'Last Name', 'required');
		$this->form_validation->set_rules('npin', 'National Provider Identification Number', 'required');
		$this->form_validation->set_rules('business_name', 'Business Name', 'required');
		$this->form_validation->set_rules('business_address', 'Business Address', 'required');
		$this->form_validation->set_rules('phone_num', 'Phone Number', 'required');
		$this->form_validation->set_rules('email', 'Email', 'required|valid_email|is_unique[users.email]');
		$this->form_validation->set_rules('password', 'Password', 'required|min_length[6]|max_length[14]|matches[confirm_password]');
		$this->form_validation->set_rules('confirm_password', 'Password Confirmation', 'required|min_length[6]|max_length[14]');
		$this->form_validation->set_rules('captcha', "Captcha", 'required|callback_captcha_validation');
    
		/* Check if form (and captcha) passed validation*/
		if ($this->form_validation->run()) {
			/* Clear the session variable */
			$this->session->unset_userdata('captchaWord');
			
			// create user array
			$user_data = array(
				'type'			=> 2,
				'first_name' 	=> $this->input->post('first_name'),
				'last_name' 	=> $this->input->post('last_name'),
				'password'	 	=> $this->encrypt->encode($this->input->post('password')),
				'email'			=> $this->input->post('email'),
				'active'		=> 0
			);
			
			// create provider array
			$provider_data = array (
				'user_id'			=> $id,
				'npin' 				=> $this->input->post('npin'),
				'business_name' 	=> $this->input->post('business_name'),
				'business_address' 	=> $this->input->post('business_address'),
				'phone_num'			=> $this->input->post('phone_num'),
				'cell_num'			=> ($this->input->post('cell_num') ? $this->input->post('cell_num') : NULL)
			);
			
			/* insert data into the database */
			$this->user_model->insert_provider($user_data, $provider_data);
			
			// /* log the customer in */
			$q = $this->user_model->get_user($this->input->post('email'));
			
			if($q ) {
				$this->session->set_userdata('logged_in' ,TRUE);
				$this->session->set_userdata('user_id', $this->user_model->get_user_id($this->input->post('username')));
				$this->session->set_userdata('first_name', $q['first_name']);
				$this->session->set_userdata('last_name', $q['last_name']);
			}
			/************************/
			/*    Standard Info     */
			/************************/
			redirect('login', 'refresh');
		}
		else {
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
			$this->session->set_userdata('captchaWord', $data['captcha']['word']);
			
			/************************/
			/*    Standard Info     */
			/************************/
			$data['header_info'] = "Please complete all fields:";
			$data['view'] = 'register_provider';
			$this->load->view('init', $data);
		}
		
	}
	
	/***************************************************************************
	|--------------------------------------------------------------------------
	| captcha_validation
	|--------------------------------------------------------------------------
	|
	| Compares the captcha word generated to the captcha word submitted by the
	| user.
	|
	***************************************************************************/		
	function captcha_validation($captcha) {
		if(strtoupper($this->session->userdata('captchaWord')) == strtoupper($captcha)) {	
			return TRUE;
		}
		
		$this->form_validation->set_message('captcha_validation', 'The %s field must match the captcha image');
		return FALSE;
	}
}
/**** END OF FILE ****/