<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Notifications
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class notifications extends StepRite_Controller {
	function __construct() {
		parent::__construct();
		$this->user->provider_logged_in();
	}

	public function index() {
		$data = NULL;
		/************************/
		/*    Load File View    */
		/************************/
		$this->load->view('dashboard/notifications', $data);
	}
}