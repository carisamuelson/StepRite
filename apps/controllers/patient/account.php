<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Login (Users)
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class account extends StepRite_Controller {
	
	function __construct() {
		parent::__construct();
		$this->user->patient_logged_in();
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
		$patient = $this->user_model->get_patient_by_id($this->session->userdata('user_id'));

		if($patient) {
			$data['patient'] = $patient;
		}
		else {
			$this->session->set_userdata('notice', 'Unable to retrieve your information. Please try logging in again or contact customer support.');
		}
		
		/************************/
		/*    Load File View    */
		/************************/
		$data['header_info'] = "
			<table id=\"tables\">
				<tr>
					<td class=\"header\"> Patient: <strong>" . $patient['last_name'] . ", " . $patient['first_name'] . "</strong> </td>
					<td class=\"header\"> MRN: <strong>" . $patient['mrn'] . "</strong> </td>
					<td class=\"header\"> Height: <strong>" . $patient['height'] . " inches </strong> </td>
					<td class=\"header\"> Weight: <strong>" . $patient['weight'] . " pounds </strong> </td>
					<td class=\"header\"> Doctor: <strong>" . $patient['dr'] . "</strong> </td>
				</tr>
			</table>";
			
		$data['view'] = 'patient/account';
		$this->load->view('init', $data);
	}
}
/**** END OF FILE ****/