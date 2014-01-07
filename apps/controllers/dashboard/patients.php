<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Patients
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class patients extends StepRite_Controller {
	function __construct() {
		parent::__construct();
		$this->user->provider_logged_in();
		$this->load->model('user_model');
	}

	public function index() {
		$data['patients'] = $this->user_model->get_patients($this->session->userdata('user_id'));
		$data['patient'] = $this->user_model->get_patient_by_id($this->session->userdata('patient_id'));
		/************************/
		/*    Load File View    */
		/************************/
		$this->load->view('dashboard/patients', $data);
	}
	
	public function edit() {
	
		$this->form_validation->set_rules('extended_date', "extended_date", 'required|valid_date');
		
		if(!$this->form_validation->run()) {
			echo "error";
		} 
		else {
			echo "You've successfully updated your patient with id = " . $this->input->post('id');
			echo "<br/><br/>";
		}
	}
}