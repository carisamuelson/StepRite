<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');
class Auth {


	public function logged_in() {
		return (bool)$this->session->userdata('identity');
	}
	
	public function get_user_id() {
		$user_id = $this->session->userdata('user_id');
		if (!empty($user_id)) {
			return $user_id;
		}
		return null;
	}
	
	public function logout() {
		$this->session->unset_userdata(array($identity => '', 'id' => '', 'user_id' => '') );
		//Destroy the session
		$this->session->sess_destroy();
		//Recreate the session
		$this->session->sess_create();
		$this->set_message('logout_successful');
		return TRUE;
	}	

	
	public function login($username) {
		$this->session->set_userdata('user_id', $this->user_model->get_user_id($this->input->post('username')));
		$this->session->set_userdata('first_name', $q['first_name']);
		$this->session->set_userdata('last_name', $q['last_name']);
	}
}

