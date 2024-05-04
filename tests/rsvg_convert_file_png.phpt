--TEST--
rsvg_convert_file PNG test
--FILE--
<?php
var_dump(rsvg_convert_file('qrcode.svg', 'qrcode.png', 'png'));

?>
--EXPECT--
bool(true)
