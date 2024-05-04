--TEST--
rsvg_convert_file EPS test
--FILE--
<?php
var_dump(rsvg_convert_file('qrcode.svg', 'qrcode.eps', 'eps'));

?>
--EXPECT--
bool(true)
