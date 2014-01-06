<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| New_patient
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class New_patient extends Custom_Controller {

	/***************************************************************************
	|--------------------------------------------------------------------------
	| Index
	|--------------------------------------------------------------------------
	|
	| Displays the start information related to this class
	|
	***************************************************************************/		
	function index() {
		/* Validate the form */
		$this->form_validation->set_rules('mrn', 'Medical Record Number', 'required|alpha_dash');
		$this->form_validation->set_rules('first_name', 'Patient\'s First Name:	', 'required|min_length[3]|max_length[20]');
		$this->form_validation->set_rules('last_name', 'Patient\'s Last Name:', 'required|min_length[3]|max_length[20]');
		$this->form_validation->set_rules('phone_num', 'Patient\'s Phone Number:', 'required|numeric|min_length[9]|max_length[9]');
		$this->form_validation->set_rules('email', 'Patient\'s Email:	', 'required|valid_email|is_unique[users.email]');
		$this->form_validation->set_rules('dr', 'Name of Patient\'s Doctor:	', 'required|min_length[3]|max_length[60]');
		$this->form_validation->set_rules('height', 'Patient\'s Height in Inches:	', 'required|numeric|min_length[2]|max_length[2]');
		$this->form_validation->set_rules('weight', 'Patient\'s Weight in Pounds:', 'required|numeric|min_length[2]|max_length[3]');
		$this->form_validation->set_rules('start_date', 'Start Date', 'required|valid_date');
		$this->form_validation->set_rules('end_date', 'End Date', 'required|valid_date');
		$this->form_validation->set_rules('pressure', 'Pressure Percentage', 'required');
		
		if($this->form_validation->run()) {
			// create user array
			$user_data = array(
				'type'			=> 2,
				'first_name' 	=> $this->input->post('first_name'),
				'last_name' 	=> $this->input->post('last_name'),
				'email'			=> $this->input->post('email'),
				'active'		=> 0,
			);
			// create patient data array
			$patient_data = array (
				'provider_id'		=> $this->session->userdata('user_id'),
				'mrn'				=> $this->input->post('mrn'),
				'start_date'		=> $this->input->post('start_date'),
				'end_date'			=> $this->input->post('end_date'),
				'reg_date'			=> date("Y-m-d"),			
				'weight'			=> $this->input->post('weight'),
				'height'			=> $this->input->post('height'),
				'pt'				=> ($this->input->post('pt') ? $this->input->post('pt') : NULL),
				'dr'				=> $this->input->post('dr'),	
				'injured_leg'		=> $this->input->post('injured_leg'),
				'times'				=> $this->input->post('times'),
				'phone_num'			=> $this->input->post('phone_num'),
				'pt'				=> $this->input->post('pt'),
				);
		
			$this->load->model('user_model');
			$this->user_model->insert_patient($user_data, $patient_data);

			/************************/
			/*    Load File View    */
			/************************/
			$this->session->set_userdata('notice', 'Thank you for registering your new patient. We will validate the information provided before the patient is activated');
			redirect('dashboard/view_patients', 'refresh');
		}
		else {
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = "Please complete all fields:";
			$data['view'] = 'account/new_patient';
			$this->load->view('init', $data);
		}
	}
}
/**** END OF FILE ****/