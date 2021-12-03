## Trie 
A Trie data structure for strings in JS

#### Install
```
npm i @joenano/trie
```

#### Import

```js
const Trie = require('@joenano/trie');
```

#### Insert

```js

const trie = new Trie();

var strings = ['string 1', 'string 2', 'string 3'];

for(string of strings) {
    trie.insert(string);
}
```

#### Contains
Check if string exists in trie. Returns false for substrings.

```js
if(trie.contains('string 1')) {
    console.log('string found');
}
```

#### Find
Returns array of strings with a given prefix.

```js
var found = trie.find('str');

console.log(found);
// ['string 1', 'string 2', 'string 3']
```

#### Remove

```js
trie.remove('string 1');

found = trie.find('str');

console.log(found);
// ['string 2', 'string 3']
```

#### Caching
Array results of find are cached by default, you can disbale this by setting caching to false.

```js
trie.caching = false;
```

The cache is cleared automatically if a string is removed from the trie, but if you insert after the initial build you will have to manually clear the cache.

```js
trie.insert('new string');
trie.clearCache();

```

#### String count

```js
console.log('Strings in trie: ', trie.stringCount);
```
