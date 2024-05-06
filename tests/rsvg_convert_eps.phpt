--TEST--
rsvg_convert EPS test
--FILE--
<?php
var_dump(! empty(rsvg_convert(file_get_contents('qrcode.svg'), 'eps', '#ffffff')));

?>
--EXPECT--
bool(true)
