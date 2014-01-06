<div class="content">
	<div class="left-box">
		<?php echo form_open('admin/create_admin'); ?>

		Username:
		<input type="text" size="35" id="username" name="username" value="<?php echo set_value('username'); ?>" />
		
		First Name:
		<input type="text" size="35" id="first_name" name="first_name" value="<?php echo set_value('first_name'); ?>" />
		
		Last Name:
		<input type="text" size="35" id="last_name" name="last_name" value="<?php echo set_value('last_name'); ?>" />

		Email Address:
		<input type="text" size="35" id="email" name="email" value="<?php echo set_value('email'); ?>" />

		Password:
		<input type="password" size="35" id="password" name="password" value="<?php echo set_value('password'); ?>" />
		
		Confirm Password:
		<input type="password" size="35" id="confirm_password" name="confirm_password" value="<?php echo set_value('confirm_password'); ?>" /><br/>
		
		Type:<br/>
		<input type="radio" name="type" value="1" checked> Full Administrator<br/>
		<input type="radio" name="type" value="2"> Customer Service<br/>
		<input type="radio" name="type" value="3"> Distribution<br/><br/>
		
		<?php echo form_submit('submit','Submit');  ?>
		<?php echo form_close(); ?>
	</div>
</div>

<div class="content">
	<div class="right-box">
	</div>
</div>