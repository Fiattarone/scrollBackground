const l10n = require('../helpers/l10n').default;

const id = 'EVENT_IF_ACTOR_DESTROYED';
const groups = ['EVENT_GROUP_CONTROL_FLOW', 'EVENT_GROUP_ACTOR'];

const autoLabel = (fetchArg) => {
	return l10n('If Actor Deactivated', {
		actor: fetchArg('actorId'),
	});
};

const fields = [
	{
		key: 'actorId',
		label: l10n('ACTOR'),
		description: l10n('FIELD_ACTOR_CHECK_DESC'),
		type: 'actor',
		defaultValue: '$self$',
	},
	// {
	// 	key: 'output',
	// 	label: 'Variable',
	// 	type: 'variable',
	// 	default: 'LAST_VARIABLE',
	// },
	{
		key: 'output',
		label: l10n('FIELD_VARIABLE'),
		description: l10n('FIELD_VARIABLE_DESC'),
		type: 'variable',
		defaultValue: 'LAST_VARIABLE',
	},
	{
		key: 'debug',
		label: 'Debug Actor Idx',
		type: 'variable',
		default: 'LAST_VARIABLE',
	},

	{
		key: 'true',
		label: l10n('FIELD_TRUE'),
		description: l10n('FIELD_TRUE_DESC'),
		type: 'events',
	},
	{
		key: '__collapseElse',
		label: l10n('FIELD_ELSE'),
		type: 'collapsable',
		defaultValue: true,
		conditions: [
			{
				key: '__disableElse',
				ne: true,
			},
		],
	},
	{
		key: 'false',
		label: l10n('FIELD_FALSE'),
		description: l10n('FIELD_FALSE_DESC'),
		conditions: [
			{
				key: '__collapseElse',
				ne: true,
			},
			{
				key: '__disableElse',
				ne: true,
			},
		],
		type: 'events',
	},
];

const compile = (input, helpers) => {
	const {
		_callNative,
		getVariableAlias,
		_addComment,
		_stackPop,
		_stackPushConst,
		_stackPush,
		actorPushById,
		getActorIndex,
		ifScriptValue,
		ifVariableValue,
		// _stackPushRef,
		// variableSetToScriptValue,
		// _declareLocal,
	} = helpers;
	const truePath = input.true;
	const falsePath = input.__disableElse ? [] : input.false;

	// const tmp0 = _declareLocal('tmp0', 1, true);

	// variableSetToScriptValue(tmp0, input.actorId);
	const variableAlias = getVariableAlias(input.output);
	// const actorDebugVariableAlias = getVariableAlias(input.debug);

	_addComment('If actor is destroyed');

	_stackPushConst(variableAlias);
	// _stackPushConst(actorDebugVariableAlias);
	_stackPushConst(getActorIndex(input.actorId));
	_callNative('script_cmd_if_actor_destroyed');

	_stackPop(2);

	// ifScriptValue(
	// 	{ type: 'variable', value: input.output },
	// 	truePath,
	// 	falsePath
	// );

	ifVariableValue(input.output, '.EQ', 0, truePath, falsePath);
};

module.exports = {
	id,
	description: l10n('EVENT_IF_ACTOR_DESTROYED_DESC'),
	autoLabel,
	groups,
	fields,
	compile,
	// Presets can be added here if desired.
	presets: [],
};
