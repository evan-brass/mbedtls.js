export const encoder = new TextEncoder();
export const decoder = new TextDecoder();

export class OutOfMemoryError extends Error {
	constructor() {
		super("Out of Memory");
	}
}
