<div class="content">
	<div class="left-box">
		<?php echo form_open('patient/change_password'); ?>
		
		Current Password:
		<input type="password" size="35" id="current_password" name="current_password" value="<?php echo set_value('current_password'); ?>" />
	
		New Password:
		<input type="password" size="35" id="password" name="password" value="<?php echo set_value('password'); ?>" />
		
		Confirm New Password:
		<input type="password" size="35" id="confirm_password" name="confirm_password" value="<?php echo set_value('confirm_password'); ?>" /><br/>

		<?php echo form_submit('submit','Submit');  ?>
		<?php echo form_close(); ?>
	</div>
</div>