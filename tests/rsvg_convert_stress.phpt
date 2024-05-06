--TEST--
rsvg_convert stress test
--FILE--
<?php

for ($i = 0; $i < 100; $i++) {
    rsvg_convert(file_get_contents('qrcode.svg'), 'eps', '#ffffff');
    rsvg_convert(file_get_contents('qrcode.svg'), 'png', '#ffffff');
    rsvg_convert(file_get_contents('qrcode.svg'), 'pdf', '#ffffff');
    rsvg_convert(file_get_contents('qrcode.svg'), 'svg', '#ffffff');
}

?>
--EXPECT--
