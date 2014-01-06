<table class="tables">
<tr class="patient">
	<th class="patient">Name</strong></th>
	<th class="patient">MRN</th>
	<th class="patient">Height</strong></th>
	<th class="patient">Weight</strong></th>
	<th class="patient">Doctor</th>
	<th class="patient"></th>
</tr>	
<?php foreach($patients->result_array() as $row) { ?>	 
		<tr class="patient">
			<td class="patient"><?php echo $row['last_name'] . ", " . $row['first_name']; ?></td>
			<td class="patient"><?php echo $row['mrn']; ?></td>
			<td class="patient"><?php echo $row['height']; ?></td>
			<td class="patient"><?php echo $row['weight']; ?></td>
			<td class="patient"><?php echo $row['dr']; ?></td>
			<td class="patient"><a class="edit-patient">Edit Patient</a></td>
		</tr>
<?php } ?>
</table>

<div id="edit-dialog" title="Create new user">
	<?php echo form_open('dashboard/patients/edit', array('id' => 'edit-form')); ?>
		<strong>Extend Patient Treatment Date</strong>
		Treatment Start Date: <?php echo $patient['start_date']; ?> <br/>
		Initial Treatment End Date: <?php echo $patient['end_date']; ?><br/>
		Treatment End Date Extension	:	2014-01-16 (as of 2013-12-31 22:51:19)
		The Treatment End Date for this patient is 11 days away.
	<?php echo form_close(); ?>
</div>

<script><!--
$(document).ready(function() {
	// Styling for the patient table
	$("tr:even").css( "background-color", "#E9E9E9" );
	$("tr").css( "border-top", "1px solid #000000" );
	$("tr.patient:last").css( "border-bottom", "1px solid #000000" );

	// Edit Patient Dialog Popup
	$( ".edit-patient" ).click(function() {
		$(" #edit-dialog" ).dialog({ show: 'fade' });
		$( "#edit-dialog" ).dialog( "open" ).fadeIn(1000);
		$(".ui-dialog-titlebar").hide();
	});
	  
	$( "#edit-dialog" ).dialog({
		autoOpen: false,
		resizable: false,
		height: 500,
		width: 300,
		modal: true,
		buttons: {
			"Update Patient": function() {
				$.ajax({
					type: "POST",
					url: "<?php echo base_url() . "dashboard/patients/edit" ?>",
					data: $("#edit-form").serialize(),
					success: function(data) {
						$( "#edit-dialog" ).html(data);
					}
				});
			},
			Cancel: function() {
			  $( this ).dialog( "close" );
			}
		},
    });
});
</script>