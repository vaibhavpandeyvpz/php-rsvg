--TEST--
rsvg_convert PNG test
--FILE--
<?php
var_dump(! empty(rsvg_convert(file_get_contents('qrcode.svg'), 'png', '#ffffff')));

?>
--EXPECT--
bool(true)
