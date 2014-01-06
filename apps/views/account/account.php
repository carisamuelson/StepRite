<div class="content">
	<div class="left-box">
		<table id="tables">
			<colgroup>
				<col class="left" />
				<col class="right" />
			</colgroup>
			<tr>
				<td class="left">First Name:</td>
				<td class="right"><?php echo $provider['first_name']; ?></td>
			</tr>
			<tr>
				<td class="left">Last Name:</td>
				<td class="right"><?php echo $provider['last_name']; ?></td>
			</tr>			
			<tr>
				<td class="left">NPIN:</td>
				<td class="right"><?php echo $provider['npin']; ?></td>
			</tr>
			<tr>
				<td class="left">Email:</td>
				<td class="right"><?php echo $provider['email']; ?></td>
			</tr>		
			<tr>
				<td class="left">Business Name:</td>
				<td class="right"><?php echo $provider['business_name']; ?></td>
			</tr>		
			<tr>
				<td class="left">Business Address:</td>
				<td class="right"><?php echo $provider['business_address']; ?></td>
			</tr>
			<?php if($provider['phone_num']) { ?>
			<tr>
				<td class="left">Phone Number:</td>
				<td class="right"><?php echo $provider['phone_num']; ?></td>
			</tr>
			<?php } ?>

			<?php if($provider['cell_num']) { ?>			
			<tr>
				<td class="left">Cell Phone Number:</td>
				<td class="right"><?php echo $provider['cell_num']; ?></td>
			</tr>
			<?php } ?>
			<?php /*<tr>
				<td class="center" colspan="2">
					<br /><br /><a href="<?php echo base_url() . "account/account/edit_information";?>" class="anchor">Edit Contact Information</a>
				</td>
			</tr>
			*/ ?>
		</table>
	</div>
</div>

<div class="content">
	<div class="right-box">
		<ul>
			<li><?php echo anchor('account/new_patient', 'Register New Patient'); ?></li>
			<?php /* <li><?php echo anchor('account/account/edit_information', 'Change Personal Information'); ?></li> */ ?>
			<li><?php echo anchor('account/change_password', 'Change Your Password'); ?></li>
		</ul>
	</div>
</div>