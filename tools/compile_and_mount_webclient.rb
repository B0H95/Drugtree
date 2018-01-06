mount_dir = "/srv/www/drugtree"
source = "index.html build/bundle.js"

out = %x{ cd ../webclient && npm run compile && cp -t #{mount_dir} #{source} }
puts out