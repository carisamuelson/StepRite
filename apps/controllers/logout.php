<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Logout (Users)
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Logout extends StepRite_Controller {
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Index
	|--------------------------------------------------------------------------
	|
	| Displays the start information related to this class
	|
	***************************************************************************/	
	public function index() {
		$this->session->unset_userdata('logged_in');
		$this->session->sess_destroy();
		redirect('login');
	}
}
/**** END OF FILE ****/