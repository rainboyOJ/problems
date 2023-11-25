const routes = [
	{
		path: '/',
		name: 'index',
		component: () => import('@/views/index.vue') //.vue不可省略
	}
]

export default routes
