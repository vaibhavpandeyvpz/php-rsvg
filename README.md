# php-rsvg

[PHP](https://www.php.net/) extension based on [RSVG](https://gitlab.gnome.org/GNOME/librsvg) library to quickly convert SVG files into EPS, PDF, PNG and SVG again.

## Requirements

* [PHP](https://www.php.net/) 7.x or 8.x
* [cairo](https://www.cairographics.org/) (tested with 1.18.0)
* [librsvg](https://gitlab.gnome.org/GNOME/librsvg) (tested with 2.58.0)

## Installation

To build and install the module, clone the project and run below command:

```shell
phpize
./configure
make
make install
```

Then enable the extension in your `php.ini`

```shell
extension=rsvg.so
```

To try out the extension, you can run the following command

```shell
php -a -d extension=modules/rsvg.so
```

## Usage

Once loaded, you can use below functions to process SVG files:

```php
<?php

// read SVG file contents
$svg_contents = file_get_contents('qrcode.svg');

// convert from SVG to PNG
$png_contents = rsvg_convert($svg_contents, 'png', '#ffffff'); // can also pass 'eps', 'pdf' or 'svg'

// can also convert b/w files directly
rsvg_convert_file('qrcode.svg', 'qrcode.png', 'png', '#ffffff');
```

In above examples, `#ffffff` is the background color to be used for output.
To output an image with transparent background, supply an empty string i.e., `''`.
