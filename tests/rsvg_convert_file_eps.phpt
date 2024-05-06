--TEST--
rsvg_convert_file EPS test
--FILE--
<?php
var_dump(rsvg_convert_file('qrcode.svg', 'qrcode.eps', 'eps', '#ffffff'));

?>
--EXPECT--
bool(true)
