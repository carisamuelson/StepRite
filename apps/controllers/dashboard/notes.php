<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Notes
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class notes extends Custom_Controller {
	function __construct() {
		parent::__construct();
	}

	public function index() {
		$data = NULL;
		/************************/
		/*    Load File View    */
		/************************/
		$this->load->view('dashboard/notes', $data);
	}
}