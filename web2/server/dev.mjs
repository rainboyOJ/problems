import { spawn } from 'node:child_process';

const npmCommand = process.platform === 'win32' ? 'npm.cmd' : 'npm';
const build = spawn(npmCommand, ['run', 'build'], { stdio: 'inherit' });

let server;

function stop() {
  build.kill('SIGTERM');
  server?.kill('SIGTERM');
}

build.on('close', (code) => {
  if (code !== 0) process.exit(code || 1);
  server = spawn(process.execPath, ['server/index.mjs'], { stdio: 'inherit' });
  server.on('close', (serverCode) => process.exit(serverCode || 0));
});

process.on('SIGINT', stop);
process.on('SIGTERM', stop);
