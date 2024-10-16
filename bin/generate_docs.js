#!/usr/bin/env node

import { readFileSync } from 'node:fs';
import { globSync } from 'node:fs';
import { join } from 'node:path';

const globSyncSort = (path) => {
  return globSync(path).sort((a, b) => {
    if (a.endsWith('README.md')) return -1;
    if (b.endsWith('README.md')) return 1;
    return a.localeCompare(b);
  });
};

const writeFileToOutput = (path) =>
  process.stdout.write(`${readFileSync(join(path), 'utf8')}\n`);

const writeFilesToOutput = (paths) => paths.map(writeFileToOutput);

writeFilesToOutput([
  './Documentation/README.md',
  './Documentation/Platforms.md',
  './Documentation/Install.md',
]);

process.stdout.write('## Usage\n\n');

writeFilesToOutput([
  ...globSyncSort('./Documentation/Audio/*.md'),
  ...globSyncSort('./Documentation/Common/*.md'),
  ...globSyncSort('./Documentation/Parsers/*.md'),
  ...globSyncSort('./Documentation/Utilities/*.md'),
]);

writeFilesToOutput([
  './Documentation/Architecture.md',
  './Documentation/Git Hooks.md',
  './Documentation/Testing.md',
  './Documentation/Build.md',
  './Documentation/Contributing.md',
  './Documentation/Community Roadmap.md',
  './Documentation/License.md',
]);
