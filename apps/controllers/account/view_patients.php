<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| View_patients
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class View_patients extends Custom_Controller {
	/***************************************************************************
	|--------------------------------------------------------------------------
	| Index
	|--------------------------------------------------------------------------
	|
	| Displays the start information related to this class
	|
	***************************************************************************/	
	function index() {
		/************************/
		/*    Load File View    */
		/************************/
		$data['header_info'] = "Under Construction";
		$data['view'] = 'account/view_patients';
		$this->load->view('init', $data);
	}
}
/**** END OF FILE ****/