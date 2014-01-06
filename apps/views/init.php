<?php
		/* Load the Header View */
		$this->load->view('common/header');
		/************************/
		/*    Load File View    */
		/************************/
		$this->load->view($view);
		/* Load the Footer View */
		$this->load->view('common/footer');	
?>
