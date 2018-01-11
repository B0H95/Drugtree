let makeRequest = (method, endpoint, body, callback) => {
    let xhr = new XMLHttpRequest();
    xhr.open(method, endpoint, true);
    xhr.onload = () => {
        callback({
            response: xhr.responseText,
            status: xhr.status
        });
    };
    xhr.send(body);
};

module.exports = {
    get: (endpoint, body, callback) => {
        makeRequest("GET", endpoint, body, callback);
    },

    post: (endpoint, body, callback) => {
        makeRequest("POST", endpoint, body, callback);
    },

    put: (endpoint, body, callback) => {
        makeRequest("PUT", endpoint, body, callback);
    },

    delete: (endpoint, body, callback) => {
        makeRequest("DELETE", endpoint, body, callback);
    }
};