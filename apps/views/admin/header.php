<!DOCTYPE html>
<html lang="en">
<head>
<title>StepRite - Administration</title>
<!--<base href="<?php echo base_url();?>">-->
<link rel="shortcut icon" href='<?php echo base_url() . "favicon.ico";?>'>
<meta http-equiv='content-type' content='text/html;charset=UTF-8'>

<!-- StyleSheets -->
<link rel='stylesheet' type='text/css' href='<?php echo base_url() . "includes/css/stylesheet.css";?>' />
<link rel='stylesheet' type='text/css' href='<?php echo base_url() . "includes/js/jquery-ui/themes/base/jquery-ui.css";?>' />
<link rel='stylesheet' type='text/css' href='http://fonts.googleapis.com/css?family=Roboto+Condensed:400,700' />

<!-- JavaScript -->
<script type="text/javascript" src='<?php echo base_url() . "includes/js/jquery.js";?>' \></script>
<script type="text/javascript" src='<?php echo base_url() . "includes/js/jquery-ui/ui/jquery-ui.min.js";?>' \></script>
<script type='text/javascript' src='<?php echo base_url() . "includes/js/ckeditor/ckeditor.js" ?>' /></script>

</head>
<body>
<div id="mainWrap">

<!-- HEADER BEGIN -->
<div id="header">
	<div id="logo"><a href="<?php echo base_url(); ?>"><img src="<?php echo base_url() . "images/sr_logo.png";?>" alt="StepRite Logo" height="160" width="272"></a></div>
	<span class="mission">Admin Area<span>
</div>
<!-- END HEADER -->

<!-- MENU BEGIN -->
<div id="red-bar">
	<?php if($this->session->userdata('admin_logged_in')) { ?>
	<ul>
		<li><a href="<?php echo base_url() . "admin/admin";?>">Admin Home</a></li>
		<li><a href="<?php echo current_url() . "#"?>">User Management</a></li>
		<li><a href="<?php echo base_url() . "admin/articles";?>">Articles</a></li>
		
		<?php if($this->session->userdata('admin_type') == 1) { ?>
			<li><a href="<?php echo base_url() . "admin/create_admin";?>">Create Admin</a></li>
		<?php } ?>
		
		<li><a href="<?php echo base_url() . "admin/logout";?>">Logout</a></li>
	</ul>	
	<?php } ?>
	<span class="time">
		<?php
			$today = getdate(); 
			echo $today["weekday"] . ", " . $today["month"] . " " . $today["mday"] . ", " . $today["year"];
		?>
	</span>

	
	
</div>
<!-- END MENU -->

<!-- CONTENT BEGIN -->
<div id="content">

<?php if(isset($header_info) || $this->session->userdata('success') || $this->session->userdata('notice') || validation_errors()) { ?>
<div class="content">
	<div class="box">	
		<?php if(isset($header_info)) { echo $header_info; } ?>
		<?php if($this->session->userdata('success')) {echo "<br /><span>" . $this->session->userdata('success') . "</span>"; } ?>
		<?php if($this->session->userdata('notice')) {echo "<br /><span class=\"error\">" . $this->session->userdata('notice') . "</span>"; } ?>
		<?php echo "<span class=\"error\">" . validation_errors() . "</span>"; ?>
	</div>

	<?php
		$this->session->unset_userdata('success');
		$this->session->unset_userdata('notice');
	?>
</div>
<?php } ?>