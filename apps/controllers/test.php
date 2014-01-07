<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Test
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 06 January 2014
| All information included is copyrighted MedHab, LLC 2013-2014
|
***************************************************************************/
class test extends StepRite_Controller {
	function __construct() {
		parent::__construct();
	}

	public function index() {
		$this->load->library('user');
		
		
		
		if($id = $this->user->is_valid($email, $password)) {
			/* Do something with $id */
		}
		else {
			/* validity failed */
		}
	}
}