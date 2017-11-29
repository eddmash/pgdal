
PACKAGE
-------

pgdal is a PHP 5 module that provides PHP bindings to the GDAL/OGR library.

The build requires GDAL 1.7 or above.

This binding is based on the GDAL C API.

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

OGRRegisterAll();
$ds = OGROpen('usa_states/usa_state_shapefile.shp');
if ($ds):
    echo "DATASOURCE NAME :: ".OGR_DS_GetName($ds)."<br>";
    $lcount = OGR_DS_GetLayerCount($ds);
    echo "LAYER COUNT :: ".$lcount."<br>";
    for($i=0; $i< $lcount; $i++){
        echo "-LAYER  :: ".$i."<br>";
        $layer = OGR_DS_GetLayer($ds, $i);
        if($layer):
            $fcount = OGR_L_GetFeatureCount($layer);
            echo "-FEATURE COUNT :: ".$fcount."<br>";

            for($fi=0; $fi< $fcount; $fi++){
                $feature = OGR_L_GetFeature($layer, $fi);
                if($feature):
                    $fieldCount = OGR_F_GetFieldCount($feature);
                    echo "-- Feature $fi <br>";
                    echo "---- FIELD COUNT :: ".$fieldCount."<br>";
                    $fields = [];
                    for($fli=0; $fli< $fieldCount; $fli++){
                        $fieldDfn = OGR_F_GetFieldDefnRef($feature, $fli);
                        $type = OGR_Fld_GetType($fieldDfn);
                        $typeName = OGR_GetFieldTypeName($type);
                        $fields[] = OGR_Fld_GetNameRef($fieldDfn)." <small>($typeName)</small> ";
                    }
                    echo "---- FIELDS [ ".implode(", ", $fields)." ]<br>";
                else:
                    echo "NO FEATURE FOUND <br>";
                endif;
                OGR_F_Destroy($feature);
            }

        else:
            echo "NO LAYER FOUND <br>";
        endif;
    }
else:
    echo "FAILED TO OPEN<br>";
endif;

OGR_DS_Destroy($ds);
echo "<br>";

```
