<div id="tabs">
	<ul>
		<li><a id="dashboard-anchor" href="#dashboard" />Dashboard</a></li>
		<li><a id="patients-anchor" href="<?php echo base_url() . "dashboard/patients" ?>" />Patients</a></li>		
		<li><a id="protocols-anchor" href="<?php echo base_url() . "dashboard/protocols" ?>" />Protocols</a></li>
		<li><a id="notes-anchor" href="<?php echo base_url() . "dashboard/notes" ?>" />Notes</a></li>		
		<li><a id="notifications-anchor" href="<?php echo base_url() . "dashboard/notifications" ?>" />Notifications</a></li>
	</ul>

	<div id="dashboard"></div>	
	<div id="patients"></div>
	<div id="protocols"></div>
	<div id="notes"></div>	
	<div id="notifications"></div>
</div>


<script>


$(document).ready(function() {
	//----------------------------------------------------------------------
	// jQuery Tabs
	//----------------------------------------------------------------------
	$(function() {
		$( "#tabs" ).tabs({
			beforeLoad: function( event, ui ) {
				ui.jqXHR.error(function() {
					ui.panel.html(
						"Unable to load tab informations" 
					);
				});
			}
		});
	});
	//----------------------------------------------------------------------
	// Populate the dashboard tab
	//----------------------------------------------------------------------	
	$('#dashboard').load('<?php echo base_url() . "dashboard/dashboard" ?>');
});
</script>

