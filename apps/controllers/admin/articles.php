<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
/***************************************************************************
|--------------------------------------------------------------------------
| Articles
|--------------------------------------------------------------------------
|
| Written by Matthew C. Stephens for MedHab, LLC.
| 18 December 2013
| All information included is copyrighted MedHab, LLC 2013
|
***************************************************************************/
class Articles extends StepRite_Controller {

	function __construct() {
		parent::__construct();
		if(!$this->session->userdata('admin_logged_in')  || $this->session->userdata('admin_type') != 1) {
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
		$this->form_validation->set_rules('name', 'Article Name', 'required');
		$this->form_validation->set_rules('article', 'Article ', 'required');
		
		if(!$this->form_validation->run()) {
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = "Please complete all fields";
			$data['view'] = 'admin/articles';
			$this->load->view('admin/init', $data);
		}
		else {
			$this->load->model('admin/admin_model');
			$this->admin_model->insert_article($this->input->post('name'), $this->input->post('article'));
		
		
			/************************/
			/*    Load File View    */
			/************************/
			$this->session->set_userdata('notice', 'Article successfully added');
			$data['view'] = 'admin/articles';
			$this->load->view('admin/init', $data);
		}
	}
}
/**** END OF FILE ****/