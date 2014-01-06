<?php
		/* Load the Header View */
		$this->load->view('admin/header');
		/************************/
		/*    Load File View    */
		/************************/
		$this->load->view($view);
		/* Load the Footer View */
		$this->load->view('admin/footer');		
?>
