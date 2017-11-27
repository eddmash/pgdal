
PACKAGE
-------

pgdal is a PHP 5 module that provides PHP bindings to the GDAL/OGR library.

The build requires GDAL 1.7 or above.

This module is UNSTABLE. Don't use it on production environment as it is.

Install
-------

First install `php5.6-dev`

```
sudo apt install php5.6-dev (on ubuntu)
git clone https://github.com/eddmash/pgdal.git
cd pgdal
$ /path/to/php5/bin/phpize
$ ./configure --enable-pgdal
$ make && make install
```

Enable the extension of php.ini by adding this at the end.

```extension=pgdal.so```

Usage
-----

```
var_dump("GDAL VERSION :: ".PGdal::getReleaseName());
$ds  = new DataSource('usa_states/usa_state_shapefile.shp');
echo "<br>";
var_dump("NO OF LAYERS :: ".$ds->getLayerCount());
echo "<br>";
$layer = $ds->getLayer(0);
$ldfn = $layer->getLayerDfn();
var_dump("LAYER NAME :: ".$ldfn->getName());
echo "<br>";
var_dump("NO OF FIELDS :: ".$ldfn->getFieldCount());
```
