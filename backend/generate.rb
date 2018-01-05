route_max_len = 0
routes = %x{find api/ -name "*.c"}.split.map do |route| 
    parts = route.split("/")
    file = parts[parts.length - 1]
    file = file.split(".")[0]
    dir = "/" + route.split("/")[0..-2].join("/")
    final_route = dir + "/" + file
    route_max_len = final_route.length if final_route.length > route_max_len
    {
        dir: dir,
        file: file,
        func: dir.split("/")[1..-1].join("_") + "_" + file
    }
end

get_routes = routes.map do |route| 
    route[:func] + "_get"
end

post_routes = routes.map do |route| 
    route[:func] + "_post"
end

put_routes = routes.map do |route| 
    route[:func] + "_put"
end

delete_routes = routes.map do |route| 
    route[:func] + "_delete"
end

routes_h = %{#pragma once

#include <fcgiapp.h>

#{(get_routes.map do |route|
    %{void #{route}(FCGX_Request* const request);}
end).join("\n")}
#{(post_routes.map do |route|
    %{void #{route}(FCGX_Request* const request);}
end).join("\n")}
#{(put_routes.map do |route|
    %{void #{route}(FCGX_Request* const request);}
end).join("\n")}
#{(delete_routes.map do |route|
    %{void #{route}(FCGX_Request* const request);}
end).join("\n")}

void send_request_to_handler(FCGX_Request* const request);
}

routes_c = %{#include "generated/routes.h"
#include <string.h>
#include <fcgiapp.h>

void send_request_to_handler(FCGX_Request* const request) {
    char* method = FCGX_GetParam("REQUEST_METHOD", request->envp);
    char* uri = FCGX_GetParam("REQUEST_URI", request->envp);
    if (strncmp(method, "GET", 3) == 0) {
        #{(routes.map do |route|
            full_route = route[:dir] + "/" + route[:file]
            %{if (strncmp(uri, "#{full_route}", #{route_max_len}) == 0) {
            #{route[:func] + "_get"}(request);
            return;
        }}
        end).join("\n        ")}
    }
    if (strncmp(method, "POST", 4) == 0) {
        #{(routes.map do |route|
            full_route = route[:dir] + "/" + route[:file]
            %{if (strncmp(uri, "#{full_route}", #{route_max_len}) == 0) {
            #{route[:func] + "_post"}(request);
            return;
        }}
        end).join("\n        ")}
    }
    if (strncmp(method, "PUT", 3) == 0) {
        #{(routes.map do |route|
            full_route = route[:dir] + "/" + route[:file]
            %{if (strncmp(uri, "#{full_route}", #{route_max_len}) == 0) {
            #{route[:func] + "_put"}(request);
            return;
        }}
        end).join("\n        ")}
    }
    if (strncmp(method, "DELETE", 6) == 0) {
        #{(routes.map do |route|
            full_route = route[:dir] + "/" + route[:file]
            %{if (strncmp(uri, "#{full_route}", #{route_max_len}) == 0) {
            #{route[:func] + "_delete"}(request);
            return;
        }}
        end).join("\n        ")}
    }
    FCGX_FPrintF(request->out, "{}");
}
}

File.write("./generated/routes.h", routes_h)
File.write("./generated/routes.c", routes_c)