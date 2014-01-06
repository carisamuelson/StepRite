<div class="content">
	<div class="box">
		<?php echo form_open('admin/login'); ?>
		<p>
		Username:
		<input type="text" size="35" id="username" name="username" value="<?php echo set_value('username'); ?>" />
		
		Password:
		<input type="password" size="35" id="password" name="password" />
		
		<?php echo form_submit('submit','Login');  ?>
		<?php echo form_close(); ?>
		</p>
	</div>
</div>