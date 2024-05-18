npx vite build -c ./vite.config.js --base relation
rm -rf ../../../dist/relation
mv ./dist/ ../../../dist/relation
