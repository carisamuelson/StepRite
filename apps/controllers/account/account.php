<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Account
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Account extends Custom_Controller {
	function __construct() {
		parent::__construct();

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
		$provider = $this->user_model->get_provider_by_id($this->session->userdata('user_id'));

		if($provider) {
			$data['provider'] = $provider;
		}
		else {
			$data['provider'] = "";
		}
		
		
		$data['success'] = "";
		/************************/
		/*    Load File View    */
		/************************/
		$data['header_info'] = "Account Page - Welcome " . $this->session->userdata('first_name') . " " . $this->session->userdata('last_name');
		$data['view'] = 'account/account';
		$this->load->view('init', $data);
	}
}
/**** END OF FILE ****/