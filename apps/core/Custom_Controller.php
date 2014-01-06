<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
	
	class Custom_Controller extends StepRite_Controller {
	
		function __construct() {
			parent::__construct();
			/* User failed to log in */
			if(!$this->session->userdata('logged_in') || $this->session->userdata('user_type') != 1) {
				/* Record the current url that is attempting to be accessed, and redirect to the login screen */
				$this->session->set_userdata('last_page', uri_string());
				
				/* Redirect the user to the login page */
				redirect('login', 'refresh');
			}
		}
	}
?>