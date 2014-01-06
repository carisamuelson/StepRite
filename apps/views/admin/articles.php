<div class="content">
	<div class="box">
		<?php echo form_open('admin/articles'); ?>
		<p>
		Article Name:
		<input type="text" size="35" id="name" name="name" value="<?php echo set_value('name'); ?>" />
	
		Article Message:
		<textarea class="ckeditor" name="article" rows="10" cols="50"><?php echo set_value('article_message'); ?></textarea>
		</p>
		
		<p><br /><?php echo form_submit('submit','Submit');  ?></p>
	</div>
</div>

<?php echo form_close(); ?>