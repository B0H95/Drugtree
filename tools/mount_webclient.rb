mount_dir = "/srv/www/drugtree"
source_dir = "../webclient"

%x{ cp -R #{source_dir}/* #{mount_dir} }