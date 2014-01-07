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
class Login extends StepRite_Controller {
	
	function __construct() {
		parent::__construct();
		if($this->session->userdata('logged_in')) {
			if($this->session->userdata('user_type') == 1) {
				redirect('provider/account', 'refresh');
			}
			else if($this->session->userdata('user_type') == 2) {
				redirect('patient/account', 'refresh');
			}
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
	function index() {
		$this->form_validation->set_rules('email', 'Email', 'required');
		$this->form_validation->set_rules('password', 'Password', 'required|callback__verify_login[' . $this->input->post('email') . ']');
		
		if($this->form_validation->run()) {
			$this->user->login(set_value('email'), set_value('password'));
		}
		else {
			$data['articles'] = $this->_get_articles();
			/************************/
			/*    Load File View    */
			/************************/
			$data['header_info'] = "Please login to access the dashboards:";
			$data['view'] = 'login';
			$this->load->view('init', $data);
		}
	}
	/***************************************************************************
	|--------------------------------------------------------------------------
	| _get_articles
	|--------------------------------------------------------------------------
	| @access	private protected
	| @param	none
	| @return	bool | string
	***************************************************************************/			
	private function _get_articles() {
		$this->load->model('articles_model');
		$query = $this->articles_model->get_articles();
		
		if ($query->num_rows() > 0) {
			foreach ($query->result() as $row) {
				$articles[] = array(
					'name'		=> $row->name,
					'article'	=> $row->article,
					'date'		=> $row->entry_date
				);
			}
		}
		else {
			return false;
		}

		return $articles;
	}


}
/**** END OF FILE ****/