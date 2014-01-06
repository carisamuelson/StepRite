<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Admin
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Admin extends StepRite_Controller {

	function __construct() {
		parent::__construct();
		if(!$this->session->userdata('admin_logged_in')) {
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
	public function index() {
		/************************/
		/*    Load File View    */
		/************************/
		$data['view'] = 'admin/admin';
		$this->load->view('admin/init', $data);
	}
}
/**** END OF FILE ****/