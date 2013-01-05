var http = require("http"),
	url = require("url"),
	fs = require("fs"),
	mime = require('mime'),
	path = require('path')
	qs = require('querystring');


var readAndOutputFile = function(fullPath, response){
	fs.readFile(fullPath, function(error, content) {
		if (error) {
			response.writeHead(500);
			response.end();
		}
		else {
			response.writeHead(200, { 'Content-Type': mime.lookup(fullPath) });
			response.end(content, 'utf-8');
		}
	});
};

// Create the server. Function passed as parameter is called on every request made.
// request variable holds all request parameters
// response variable allows you to do anything with response sent to the client.
http.createServer(function (request, response) {
   // Attach listener on end event.
   // This event is called when client sent all data and is waiting for response.
	var parsedUrl = url.parse(request.url, true);
	var pathName = parsedUrl.pathname;
	var fullPath = "./" + pathName;
	if(pathName.length > 2 && path.existsSync(fullPath)){
		readAndOutputFile(fullPath, response);
	} else if(pathName.indexOf("save") != -1 && request.method == "POST"){
        var body = '';
        request.on('data', function (data) {
            body += data;
            if (body.length > 1e6) {
                // FLOOD ATTACK OR FAULTY CLIENT, NUKE REQUEST
                request.connection.destroy();
            }
        });

        request.on('end', function () {
            var post = qs.parse(body);
			fs.writeFile('levels.json', post.toSave, function (err) {
			  if (err) throw err;
				response.writeHead(200);
				response.end();
			});
        });
	} else if (pathName.indexOf("get") != -1){

		readAndOutputFile("./levels.json", response);
	} else {

		readAndOutputFile("./index.html", response);
	}
// Listen on the 3333 port.
}).listen(3333);