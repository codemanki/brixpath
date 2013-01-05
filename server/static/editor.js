$(function(){
	var maxId = 0;
	var viewModel = {};

	viewModel.possibleSizes = [1,2,3,4,5,6,7,8,9]; // Board size NxN
	viewModel.possiblePathIds = [0, 1,2,3,4,5,6,7,8,9];
	viewModel.possiblePathIdsABC = [0, "A", "B", "C", "D", "E", "F","G", "H", "I", "J", "K", "L"];
	viewModel.colors = ["#EEEEEE","#CA003C", "#41CD54","#3C95E0","#33B5E5","#AA66CC","#99CC00","#FFBB33","#FF4444","#83AF9B"];
	viewModel.levels = ko.observableArray();
	viewModel.activeLevel = ko.observable({});
	
	viewModel.saveChanges = function() {
		for(var i = 0; i < this.levels().length;i++) {
			prepareLevelForDump(this.levels()[i]);
		}
		
		var toSave = ko.toJSON({"levels": ko.toJS(this.levels)});
		$.post("/save/", {"toSave":toSave})
	};
	
	viewModel.levelChangeCell = function(event, x,y){
		var _cell = this.getCellAt(x,y);
		var pathId = parseInt(event.target.value);
		if(_cell){
			if(pathId == 0) {
				this.activeLevel().cells.remove(_cell);
			} else {
				_cell.pathId(pathId);
			}
		} else {
			if(pathId == 0)
				return;
				
			_cell = new levelCell({x:x, y:y, type:"PATH_START", pathId:pathId});
			this.activeLevel().cells.push(_cell)
		}
	};
	
	viewModel.levelText = function(level){
		return level.id + " <b>" + level.rows() + "x" + level.columns() + "</b>";
	};
	
	viewModel.reloadLevelsFromSource = function(levels){
		this.levels([]);
		
		for(var i = 0; i < levels.length; i++){
			this.levels.push(new level(levels[i]));
		}
	};
	
	viewModel.addLevel = function(){
		var _level = new level({id:maxId+1, rows:1, columns:1});
		this.levels.push(_level);
		this.activeLevel(_level);
	};
	
	viewModel.getCellAt = function(x, y){
		var level = this.activeLevel();
		if(level.cells === undefined)
			return null;
			
		for(var i = 0; i < level.cells().length; i++) {
			var cell = level.cells()[i];
			if(cell.x == x && cell.y == y){
				return cell;
			}
		}
		
		return null;
	};
	
	viewModel.getCellPathAt = function(x,y){
		var cell = this.getCellAt(x,y);
		return (cell ? cell.pathId() : 0);
	};
	
	var prepareLevelForDump = function(level){
		var cells = Array.prototype.slice.call(level.cells());
		var l = cells.length;
		
		for(var i = 0; i < l; i++) {
			var c = cells[i];
			if(c && (c.x >= level.columns() || c.y >= level.rows() || parseInt(c.pathId()) === 0)){
				level.cells.remove(c);
			}
		}
		
	};
	
	var level = function(_level){
		this.id = _level.id;
		this.rows = ko.observable(_level.rows);
		this.columns = ko.observable(_level.columns);
		this.cells = ko.observableArray();
		this.comment = ko.observable("");
		
		if(this.id > maxId) {
			maxId = this.id;
		}
		
		if(_level.cells) {	
			for(var i = 0; i < _level.cells.length; i++) {
				var c = new levelCell(_level.cells[i]);
				this.cells.push(c);
			}
		}
	};
	
	var levelCell = function(_cell){
		this.x = _cell.x;
		this.y = _cell.y;
		this.type = ko.observable(_cell.type || null);
		this.pathId = ko.observable(_cell.pathId || null);
	};
	
	var editor = function(){};
	
	editor.prototype.loadLevels = function() {
		$.get("/get", function(data) {
			viewModel.reloadLevelsFromSource(data.levels);
			viewModel.activeLevel(viewModel.levels()[0]);
		});
		
	};

	ko.applyBindings(viewModel, $(".container-fluid")[0]);

	var editorInstance = new editor();
	editorInstance.loadLevels();
	
});