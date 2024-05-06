--TEST--
rsvg_convert PDF test
--FILE--
<?php
var_dump(! empty(rsvg_convert(file_get_contents('qrcode.svg'), 'pdf', '#ffffff')));

?>
--EXPECT--
bool(true)
