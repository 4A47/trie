class Node {
    constructor(parent=null, char=null) {
        this.parent = parent;
        this.children = {};
        this.char = char;
        this.isString = false;
    }
}

module.exports = class Trie {
    constructor() {
        this.root = new Node();
        this.cache = {};
        this.stringCount = 0;
        this.caching = true;
    }

    clearCache() {
        for(search in this.cache) {
            delete this.cache[search];
        }
    }

    contains(str) {
        var currentNode = this.getNode(str);

        if(currentNode) {
            if(currentNode.isString) { return true; }
        }

        return false;
    }

    dfs(node, visited, strings) {
        visited.set(node, true);

        if(node.isString) {
            strings.push(this.traceString(node));
        }

        for(var n in node.children) {
            if(!visited.has(node.children[n])) {
                this.dfs(node.children[n], visited, strings);
            }
        }
    }

    find(prefix) {
        if(this.caching && prefix in this.cache) {
            return this.cache[prefix];
        }

        var currentNode = this.getNode(prefix);

        if(currentNode !== null) {
            var strings = this.stringsFromNode(currentNode);
            
            if(this.caching) { this.cache[prefix] = strings; }

            return strings
        }

        return [];
    }

    getNode(str) {
        var currentNode = this.root;
        var len = str.length;

        for(var i = 0; i < len; i++) {
            if(str[i] in currentNode.children) {
                currentNode = currentNode.children[str[i]];
                if(i + 1 === len) { return currentNode; }
            } else { break; }
        }

        return null;
    }

    insert(str) {
        var currentNode = this.root;
        var len = str.length;

        for(var i = 0; i < len; i++) {
            if(!(str[i] in currentNode.children)) {
                var node = new Node(currentNode, str[i]);
                currentNode.children[node.char] = node;
            }

            currentNode = currentNode.children[str[i]];

            if(i + 1 === len) {
                currentNode.isString = true;
                this.stringCount++;
            }
        }
    }

    _remove(node, key) {
        delete node.children[key];

        if(Object.keys(node.children).length > 0 || node.parent === null) {
            return;
        }

        this._remove(node.parent, node.char);
    }

    remove(str) {
        var currentNode = this.getNode(str);

        if(currentNode !== null && currentNode.isString) {
            if(currentNode.children.size > 0) {
                currentNode.isString = false;
            } else {
                this._remove(currentNode.parent, currentNode.char);
            }

            this.stringCount--;
        }
    }

    stringsFromNode(node) {
        var strings = [];
        var visited = new Map();

        this.dfs(node, visited, strings);

        return strings;
    }

    traceString(node) {
        var currentNode = node;
        var str = [];
        
        while(currentNode !== null) {
            str.push(currentNode.char);
            currentNode = currentNode.parent;
        }

        return str.reverse().join('');
    }
}
