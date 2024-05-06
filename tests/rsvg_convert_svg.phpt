--TEST--
rsvg_convert SVG test
--FILE--
<?php
var_dump(! empty(rsvg_convert(file_get_contents('qrcode.svg'), 'svg', '#ffffff')));

?>
--EXPECT--
bool(true)
