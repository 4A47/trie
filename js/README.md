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
let found = trie.find('str');

// found = ['string 1', 'string 2', 'string 3']
```

#### Remove

```js
trie.remove('string 1');

let found = trie.find('str');

// found = ['string 2', 'string 3']
```


#### String count

```js
console.log('Strings in trie: ', trie.stringCount);
```

#### Case Sensitivity
Set case sensitivity for searches. False by default.

```js
trie.caseSensitive = true;
```
