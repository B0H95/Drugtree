var webpack = require("webpack");

module.exports = {
    entry: __dirname + "/index.jsx",
    module: {
        loaders: [
            {
                test: /\.jsx$/,
                exclude: /node_modules/,
                loader: "babel-loader"
            }
        ]
    },
    output: {
        path: __dirname + "/build",
        filename: "bundle.js"
    },
    plugins: [
        new webpack.optimize.UglifyJsPlugin({
            compress: {
                warnings: false
            }
        })
    ]
};